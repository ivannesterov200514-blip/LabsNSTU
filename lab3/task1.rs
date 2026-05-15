use std::io::{self, Write};

fn main() {
    println!("==============================================");
    println!(" x  |    y     |  Formula");
    println!("==============================================");
    
    print!("Введите шаг dx: ");
    stdout().flush().unwrap();
    
    let mut input = String::new();
    stdin().read_line(&mut input).unwrap();
    let dx: f64 = input.trim().parse().unwrap();

    if dx <= 0.0 {
        println!("Ошибка: шаг должен быть строго больше нуля!");
        return;
    }

    let mut x = -7.0_f64;
    while x <= 5.0 {
        let mut y: f64 = 0.0;
        let mut formula = "";
        let mut def = true;
        
        if x >= -7.0 && x <= -6.0 {
            y = -2.0 * x - 14.0;
            formula = "y1 = -2x - 14";
        }
        else if x > -6.0 && x <= -2.0 {
            let expr = 4.0 - (x + 4.0).powf(2.0);
            if expr >= 0.0 {
                y = -2.0 + expr.sqrt();
                formula = "y2 = -2 + sqrt(4-(x+4)^2)";
            } 
            else {
                def = false;
            }
        }
        else if x > -2.0 && x <= 2.0 {
            if 2.0 + x > 0.0 {
                y = (2.0 + x).log2();
                formula = "y3 = log2(2+x)";
            } 
            else {
                def = false;
            }
        }
        else if x > 2.0 && x <= 4.0 {
            let expr = 1.0 - (x - 3.0).powf(2.0);
            if expr >= 0.0 {
                y = expr.sqrt();
                formula = "y4 = sqrt(1-(x-3)^2)";
            } 
            else {
                def = false;
            }
        }
        else if x > 4.0 && x <= 5.0 {
            y = x;
            formula = "y5 = x";
        }
        else {
            def = false;
        }

        print!("{:3} | ", x);
        if def {
            print!("{:8.3} | ", y);
        } 
        else {
            print!("{:8} | ", "N/A");
        }
        println!("{}", formula);

        x += dx;
    }
    println!("==============================================");
}