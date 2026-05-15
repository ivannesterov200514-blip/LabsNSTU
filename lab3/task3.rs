use std::io::*;
use std::process;

fn main() {
    print!("Enter a, b: ");
    io::stdout().flush().unwrap();
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Input error");

    let parts: Vec<&str> = input.trim().split_whitespace().collect();
    if parts.len() < 2 {
        println!("error");
        exit(1);
    }

    let a: i32 = parts[0].parse().expect("Wrong a");
    let b: i32 = parts[1].parse().expect("Wrong b");
    if b == 1 {
        println!("infinity");
        return;
    }

    if a < 1 || a > 10 || b < 1 || b > 10 {
        println!("error");
        exit(1);
    }

    let mut sum = 0.0_f64;
    for n in 1..=100 {
        sum += (n as f64).powi(a) / (b as f64).powi(n);
    }
    let mut min_num = 1_i32;
    let mut min_den = 1_i32;
    let mut min_dif = 999.0_f64;

    for num in 1..=1000 {
        for den in 1..=1000 {
            let dif = (sum - (num as f64 / den as f64)).abs();
            if dif < min_dif {
                min_dif = dif;
                min_num = num;
                min_den = den;
            }
        }
    }
    println!("Sum: {}/{}", min_num, min_den);
}