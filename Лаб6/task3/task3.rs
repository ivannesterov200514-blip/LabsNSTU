fn print_matrix(m: &[Vec<f64>], name: &str) {
    println!("{}:", name);
    for row in m {
        print!("|");
        for &val in row {
            print!("{:10.4}", val);
        }
        println!(" |");
    }
    println!();
}

fn gauss(a: &[Vec<f64>], b: &[f64]) -> Vec<f64> {
    let n = a.len();
    let mut aug = vec![vec![0.0; n + 1]; n];
    
    for i in 0..n {
        for j in 0..n {
            aug[i][j] = a[i][j];
        }
        aug[i][n] = b[i];
    }

    print_matrix(&aug, "Исходная расширенная матрица");

    for i in 0..n {
        let mut mr = i;
        for k in i + 1..n {
            if aug[k][i].abs() > aug[mr][i].abs() {
                mr = k;
            }
        }
        if mr != i {
            aug.swap(i, mr);
        }

        for k in i + 1..n {
            let c = aug[k][i] / aug[i][i];
            for j in i..=n {
                aug[k][j] -= c * aug[i][j];
            }
        }
    }

    for i in 0..n {
        let d = aug[i][i];
        for j in i..=n {
            aug[i][j] /= d;
        }
    }

    print_matrix(&aug, "Матрица после прямого хода (единичная диагональ)");

    let mut x = vec![0.0; n];
    println!("Результаты обратного хода:");
    for i in (0..n).rev() {
        x[i] = aug[i][n];
        for j in i + 1..n {
            x[i] -= aug[i][j] * x[j];
        }
        println!("x{} = {:.4}", i + 1, x[i]);
    }
    x
}

fn check_diagonal_dominance(a: &[Vec<f64>]) {
    println!("\nПроверка диагонального преобладания:");
    let mut ok = true;
    let n = a.len();

    for i in 0..n {
        let diag = a[i][i].abs();
        let sum: f64 = (0..n)
            .filter(|&j| j != i)
            .map(|j| a[i][j].abs())
            .sum();

        print!("Строка {}: |a[{}][{}]| = {:.4}, сумма остальных = {:.4}", i + 1, i + 1, i + 1, diag, sum);
        if diag > sum {
            println!("  -> OK");
        } else {
            println!("  -> НЕ выполняется");
            ok = false;
        }
    }

    if ok {
        println!("\nУсловие сходимости выполняется.");
    } else {
        println!("\nУсловие сходимости НЕ выполняется.");
    }
}

fn seidel(a: &[Vec<f64>], b: &[f64], eps: f64, max_iter: usize) -> Vec<f64> {
    let n = a.len();
    let mut x = vec![0.0; n];
    let mut old = vec![0.0; n];

    println!("-------------------------------------------------------------");
    println!(" N        x1        x2        x3        x4        eps");
    println!("-------------------------------------------------------------");

    for iter in 1..=max_iter {
        old.copy_from_slice(&x);
        for i in 0..n {
            let mut sum = b[i];
            for j in 0..n {
                if j < i {
                    sum -= a[i][j] * x[j];
                } else if j > i {
                    sum -= a[i][j] * old[j];
                }
            }
            x[i] = sum / a[i][i];
        }

        let mut err = 0.0;
        for i in 0..n {
            err = err.max((x[i] - old[i]).abs());
        }

        println!("{:2} {:10.4} {:10.4} {:10.4} {:10.4} {:12.4}", iter, x[0], x[1], x[2], x[3], err);

        if err < eps {
            break;
        }
    }
    x
}

fn main() {
    let m_val = 0.89;
    let n_val = 0.12;
    let p_val = -1.15;

    let a = vec![
        vec![m_val, -0.04, 0.21, -1.16],
        vec![0.25, -1.23, n_val, -0.09],
        vec![-0.21, n_val, 0.8, -0.13],
        vec![0.15, -1.31, 0.06, p_val],
    ];
    let b = vec![-1.24, p_val, 2.56, m_val];

    println!("\nМетод Гаусса:");
    let xg = gauss(&a, &b);
    println!("\nРешение (Гаусс): x1={:.4}, x2={:.4}, x3={:.4}, x4={:.4}\n", xg[0], xg[1], xg[2], xg[3]);

    check_diagonal_dominance(&a);

    println!("\nМетод Зейделя:");
    let xs = seidel(&a, &b, 1e-3, 100);
    println!("\nРешение (Зейдель): x1={:.4}, x2={:.4}, x3={:.4}, x4={:.4}", xs[0], xs[1], xs[2], xs[3]);
}