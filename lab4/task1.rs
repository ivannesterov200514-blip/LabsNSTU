const EPS: f64 = 1e-4;

fn func(x: f64) -> f64 {
    2.0 * x.powi(2) + x.cos() - 6.0
}

fn diffunc(x: f64) -> f64 {
    4.0 * x - x.sin()
}

fn ph(x: f64) -> f64 {
    ((6.0 - x.cos()) / 2.0).sqrt()
}

struct Iter {
    n: usize,
    v1: f64,
    v2: f64,
    diff: f64,
}

fn halfmethod(mut a: f64, mut b: f64) -> Vec<Iter> {
    let mut table = Vec::new();
    let mut k = 0;
    
    while b - a > EPS {
        let c = (a + b) / 2.0;
        table.push(Iter { n: k, v1: a, v2: b, diff: b - a });
        
        if func(a) * func(c) < 0.0 {
            b = c;
        } else {
            a = c;
        }
        k += 1;
    }
    
    table.push(Iter { n: k, v1: a, v2: b, diff: b - a });
    table
}

fn newton(mut xn: f64) -> Vec<Iter> {
    let mut table = Vec::new();
    let mut k = 0;
    
    loop {
        let xn1 = xn - func(xn) / diffunc(xn);
        let diff = (xn1 - xn).abs();
        
        table.push(Iter { n: k, v1: xn, v2: xn1, diff });
        
        if diff <= EPS {
            break;
        }
        
        xn = xn1;
        k += 1;
    }
    
    table
}

fn simpleiter(mut xn: f64) -> Vec<Iter> {
    let mut table = Vec::new();
    let mut k = 0;
    
    loop {
        let xn1 = ph(xn);
        let diff = (xn1 - xn).abs();
        
        table.push(Iter { n: k, v1: xn, v2: xn1, diff });
        
        if diff <= EPS {
            break;
        }
        
        xn = xn1;
        k += 1;
    }
    
    table
}

fn main() {
    let hlf = halfmethod(1.0, 2.0);
    let newt = newton(2.0);
    let iter = simpleiter(1.5);

    println!("\nМетод половинного деления");
    println!("N\tan\t\tbn\t\tbn - an");
    for r in &hlf {
        println!("{}\t{:.6}\t\t{:.6}\t\t{:.6}", r.n, r.v1, r.v2, r.diff);
    }

    println!("\nМетод Ньютона");
    println!("N\txn\t\txn+1\t\txn+1 - xn");
    for r in &newt {
        println!("{}\t{:.6}\t\t{:.6}\t\t{:.6}", r.n, r.v1, r.v2, r.diff);
    }

    println!("\nМетод простых итераций");
    println!("N\txn\t\txn+1\t\txn+1 - xn");
    for r in &iter {
        println!("{}\t{:.6}\t\t{:.6}\t\t{:.6}", r.n, r.v1, r.v2, r.diff);
    }
}