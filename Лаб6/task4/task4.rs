use std::io::{self, BufRead};

fn read_board(board: &mut Vec<Vec<u8>>, n: usize, m: usize) -> bool {
    let stdin = io::stdin();
    let mut tokens = stdin.lock().lines().flat_map(|line| {
        line.unwrap().split_whitespace().map(String::from)
    });

    for i in 0..n {
        for j in 0..m {
            if let Some(token) = tokens.next() {
                match token.parse::<u8>() {
                    Ok(val) if val <= 1 => board[i][j] = val,
                    _ => return false,
                }
            } else {
                return false;
            }
        }
    }
    true
}

fn print_board(board: &[Vec<u8>]) {
    for row in board {
        for &val in row {
            print!("{:3}", val);
        }
        println!();
    }
    println!();
}

fn generate_target(n: usize, m: usize, start_val: u8) -> Vec<Vec<u8>> {
    let mid = n / 2;
    let top_val = start_val;
    let bottom_val = 1 - start_val;
    
    let mut target = Vec::with_capacity(n);
    for _ in 0..mid {
        target.push(vec![top_val; m]);
    }
    for _ in mid..n {
        target.push(vec![bottom_val; m]);
    }
    target
}

fn solve(mut board: Vec<Vec<u8>>, n: usize, m: usize, target: &[Vec<u8>], path: &mut Vec<Vec<Vec<u8>>>) -> i32 {
    path.clear();
    let mut moves = 0;

    for i in 0..n {
        for j in 0..m {
            if board[i][j] != target[i][j] {
                moves += 1;
                board[i][j] ^= 1;
                if j + 1 < m && board[i][j + 1] != target[i][j + 1] {
                    board[i][j + 1] ^= 1;
                } 
                else if i + 1 < n && board[i + 1][j] != target[i + 1][j] {
                    board[i + 1][j] ^= 1;
                } 
                else if j + 1 < m {
                    board[i][j + 1] ^= 1;
                } 
                else if i + 1 < n {
                    board[i + 1][j] ^= 1;
                } 
                else {
                    return -1;
                }
                path.push(board.clone());
            }
        }
    }

    for i in 0..n {
        for j in 0..m {
            if board[i][j] != target[i][j] {
                return -1;
            }
        }
    }
    moves
}

fn main() {
    println!("Введите размер доски N x M");
    let stdin = io::stdin();
    let mut tokens = stdin.lock().lines().flat_map(|line| line.unwrap().split_whitespace().map(String::from));

    let n = tokens.next().and_then(|s| s.parse::<usize>().ok()).expect("Не удалось прочитать N");
    let m = tokens.next().and_then(|s| s.parse::<usize>().ok()).expect("Не удалось прочитать M");

    let mut board = vec![vec![0u8; m]; n];

    println!("Введите доску (0 или 1):");
    if !read_board(&mut board, n, m) {
        eprintln!("\nОшибка ввода. Допустимы только 0 и 1.");
        return;
    }

    println!("\nДоска:");
    print_board(&board);
    println!("-----------------------------------------------");

    let target1 = generate_target(n, m, 0);
    let target2 = generate_target(n, m, 1);

    let mut path1 = Vec::new();
    let mut path2 = Vec::new();
    let moves1 = solve(board.clone(), n, m, &target1, &mut path1);
    let moves2 = solve(board.clone(), n, m, &target2, &mut path2);

    println!("Паттерн 1 (верхняя часть 0):");
    print_board(&target1);
    println!("Нужно ходов: {}", if moves1 == -1 { "невозможно" } else { moves1.to_string() });

    println!("\nПаттерн 2 (верхняя часть 1):");
    print_board(&target2);
    println!("Нужно ходов: {}", if moves2 == -1 { "невозможно" } else { moves2.to_string() });

    let mut best_moves = -1;
    let mut best_path: Option<&Vec<Vec<Vec<u8>>>> = None;

    if moves1 != -1 && moves2 != -1 {
        if moves1 <= moves2 {
            best_moves = moves1;
            best_path = Some(&path1);
        } else {
            best_moves = moves2;
            best_path = Some(&path2);
        }
    } else if moves1 != -1 {
        best_moves = moves1;
        best_path = Some(&path1);
    } else if moves2 != -1 {
        best_moves = moves2;
        best_path = Some(&path2);
    }

    if let Some(path) = best_path {
        println!("\nПуть решения:");
        for i in (0..path.len()).rev() {
            print_board(&path[i]);
        }
        println!("\nМинимальное число ходов: {}", best_moves);
    } else {
        println!("\nРешение не найдено.");
    }
}