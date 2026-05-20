use std::io::{self, BufRead};

fn read_board(board: &mut Vec<Vec<i32>>, n: usize, m: usize) -> bool {
    let mut numbers = Vec::with_capacity(n * m);
    let stdin = io::stdin();
    let mut handle = stdin.lock();
    let mut buffer = String::new();

    while numbers.len() < n * m {
        buffer.clear();
        if handle.read_line(&mut buffer).unwrap_or(0) == 0 {
            println!("\nНедостаточно данных");
            return false;
        }
        for token in buffer.split_whitespace() {
            match token.parse::<i32>() {
                Ok(val) if val == 0 || val == 1 => numbers.push(val),
                Ok(_) => {
                    println!("\nНеверно, вводим только 1 или 0");
                    return false;
                }
                Err(_) => continue,
            }
            if numbers.len() == n * m {
                break;
            }
        }
    }

    for i in 0..n {
        for j in 0..m {
            board[i][j] = numbers[i * m + j];
        }
    }
    true
}

fn print_board(board: &[Vec<i32>], n: usize, m: usize) {
    for i in 0..n {
        for j in 0..m {
            print!("{:3}", board[i][j]);
        }
        println!();
    }
    println!();
}

fn is_right(board: &[Vec<i32>], n: usize, m: usize) -> bool {
    if n == 0 || m == 0 {
        return true;
    }
    let mid = n / 2;
    let top_val = board[0][0];
    let bot_val = 1 - top_val;

    for i in 0..mid {
        for j in 0..m {
            if board[i][j] != top_val {
                return false;
            }
        }
    }
    for i in mid..n {
        for j in 0..m {
            if board[i][j] != bot_val {
                return false;
            }
        }
    }
    true
}

#[allow(dead_code)]
fn flip(x: i32, y: i32) -> (i32, i32) {
    (1 - x, 1 - y)
}

fn algo(
    board: &mut Vec<Vec<i32>>,
    n: usize,
    m: usize,
    limit: usize,
    currmove: usize,
    path: &mut Vec<Vec<Vec<i32>>>,
) -> bool {
    if is_right(board, n, m) {
        return true;
    }
    if currmove == limit {
        return false;
    }

    for i in 0..n {
        for j in 0..m - 1 {
            board[i][j] = 1 - board[i][j];
            board[i][j + 1] = 1 - board[i][j + 1];

            if algo(board, n, m, limit, currmove + 1, path) {
                path.push(board.clone());
                return true;
            }

            board[i][j] = 1 - board[i][j];
            board[i][j + 1] = 1 - board[i][j + 1];
        }
    }

    for i in 0..n - 1 {
        for j in 0..m {
            board[i][j] = 1 - board[i][j];
            board[i + 1][j] = 1 - board[i + 1][j];

            if algo(board, n, m, limit, currmove + 1, path) {
                path.push(board.clone());
                return true;
            }

            board[i][j] = 1 - board[i][j];
            board[i + 1][j] = 1 - board[i + 1][j];
        }
    }
    false
}

fn main() {
    println!("Введите размер доски N x M");
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    
    let dims: Vec<usize> = input.split_whitespace()
        .filter_map(|s| s.parse().ok())
        .collect();
    
    if dims.len() < 2 {
        eprintln!("Неверный формат ввода размеров.");
        return;
    }
    let (n, m) = (dims[0], dims[1]);

    let mut board = vec![vec![0; m]; n];

    println!("Введите доску (0 или 1):");
    loop {
        if read_board(&mut board, n, m) {
            break;
        }
    }

    println!("\nДоска:");
    print_board(&board, n, m);
    println!("-----------------------------------------------");

    let mut path: Vec<Vec<Vec<i32>>> = Vec::new();
    let mut result: i32 = -1;

    for lim in 0..=100 {
        if algo(&mut board, n, m, lim, 0, &mut path) {
            result = lim as i32;
            break;
        }
        path.clear();
    }

    if result != -1 {
        for i in (0..path.len()).rev() {
            print_board(&path[i], n, m);
        }
        println!("\nМинимальное число ходов: {}", result);
    } else {
        println!("\nРешение не найдено(или превышен лимит).");
    }
}