use std::io::{self, BufRead, Write};

fn main() {
    let stdin = io::stdin();
    let mut stdin_lock = stdin.lock();
    let stdout = io::stdout();
    let mut stdout_lock = stdout.lock();

    // Токенизатор, полностью аналогичный поведению `cin >>` (читает через пробелы/переносы строк)
    let mut line = String::new();
    let mut tokens: std::vec::IntoIter<String> = Vec::new().into_iter();

    let mut next_token = || {
        loop {
            if let Some(token) = tokens.next() {
                return token;
            }
            line.clear();
            stdin_lock.read_line(&mut line).expect("Ошибка чтения ввода");
            tokens = line.split_whitespace().map(String::from).collect::<Vec<_>>().into_iter();
        }
    };

    let mut prompt = |msg: &str| {
        stdout_lock.write_all(msg.as_bytes()).unwrap();
        stdout_lock.flush().unwrap();
    };

    let n: usize = {
        prompt("Введите количество кандидатов (n): ");
        next_token().parse().expect("Ожидалось целое число")
    };
    let k: usize = {
        prompt("Введите количество избирателей (k): ");
        next_token().parse().expect("Ожидалось целое число")
    };

    prompt("Имена кандидатов: ");
    let names: Vec<String> = (0..n).map(|_| next_token()).collect();

    let mut pref = vec![vec![0; n]; k];
    for i in 0..k {
        prompt(&format!("Голос {}: ", i + 1));
        for j in 0..n {
            let val: usize = next_token().parse().expect("Ожидался номер кандидата");
            pref[i][j] = val - 1;
        }
    }

    let mut borda = vec![0; n];
    for i in 0..k {
        for j in 0..n {
            borda[pref[i][j]] += n - 1 - j;
        }
    }

    let mut idx: Vec<usize> = (0..n).collect();
    idx.sort_by(|&a, &b| borda[b].cmp(&borda[a]));

    println!("\n====МЕТОД БОРДА====");
    for (i, &idx_val) in idx.iter().enumerate() {
        println!("{}. {} - {} баллов", i + 1, names[idx_val], borda[idx_val]);
    }

    let mut kondors = vec![0; n];
    for a in 0..n {
        for b in 0..n {
            if a == b { continue; }
            
            let mut wins = 0;
            for i in 0..k {
                for j in 0..n {
                    if pref[i][j] == a {
                        wins += 1;
                        break;
                    }
                    if pref[i][j] == b {
                        break;
                    }
                }
            }
            if wins > k / 2 {
                kondors[a] += 1;
            }
        }
    }

    idx.sort_by(|&a, &b| kondors[b].cmp(&kondors[a]));

    println!("\n====МЕТОД КОНДОРСЕ====");
    for (i, &idx_val) in idx.iter().enumerate() {
        println!("{}. {} - {} побед", i + 1, names[idx_val], kondors[idx_val]);
    }

    if kondors[idx[0]] == n - 1 {
        println!("Победитель: {}", names[idx[0]]);
    } else {
        println!("Победитель не определён (парадокс Кондорсе)");
    }
}