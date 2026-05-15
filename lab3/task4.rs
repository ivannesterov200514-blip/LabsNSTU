use std::io::*;

fn prefsum(nums: &Vec<i32>, start: usize, k: usize) -> i64 {
    let mut a: i64 = 0;
    for i in 0..k {
        a += nums[start + i] as i64;
    }
    a
}

fn main() {
    println!("Enter the number of elements in the sequence: ");
    stdout().flush().unwrap();
    
    let mut input = String::new();
    stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();
    
    if n < 5 || n > 50000 {
        println!("Input error");
        return;
    }

    println!("What is the maximum number of elements they can remove? ");
    stdout().flush().unwrap();
    
    input.clear();
    stdin().read_line(&mut input).unwrap();
    let m: usize = input.trim().parse().unwrap();
    
    println!("Enter the sequence of {} numbers: ", n);
    stdout().flush().unwrap();

    let mut nums: Vec<i32> = Vec::with_capacity(n);
    for _ in 0..n {
        input.clear();
        stdin().read_line(&mut input).unwrap();
        nums.push(input.trim().parse().unwrap());
    }

    let mut pavmove = true;
    let mut scores: [i64; 2] = [0, 0]; // scores[0] - Павел, scores[1] - Вика
    let mut lastmv: Option<usize> = None; // аналог lastmv = -1
    let mut start: usize = 0;

    while start < n {
        let max_k = std::cmp::min(m, n - start);

        let mut maxscore = std::i64::MIN;
        let mut best_k: Option<usize> = None;

        for k in 1..=max_k {
            if Some(k) == lastmv {
                continue;
            }
            let currsc = prefsum(&nums, start, k);

            if currsc > maxscore || (currsc == maxscore && best_k.map_or(true, |bk| k < bk)) {
                maxscore = currsc;
                best_k = Some(k);
            }
        }
        
        if let Some(bk) = best_k {
            if pavmove {
                scores[0] += maxscore;
            } else {
                scores[1] += maxscore;
            }

            start += bk;
            lastmv = Some(bk);
            pavmove = !pavmove;
        } else {
            break;
        }
    }

    if scores[0] > scores[1] {
        println!("Player 1 wins");
    } else {
        println!("Player 0 wins");
    }
}