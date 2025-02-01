mod command;
mod test;

use std::env;

const INPUT_FILE: &str = "./input.txt";
const CA_OUTPUT_FILE: &str = "./CA.txt";
const WA_OUTPUT_FILE: &str = "./WA.txt";

const GENERATOR_PATH: &str = "./input";
const CA_PATH: &str = "./CA";
const WA_PATH: &str = "./WA";

fn main() {
    let args: Vec<String> = env::args().collect(); // 명령줄 인수들을 벡터로 수집

    let generator_path = if args.len() == 4 {
        &args[1]
    } else { &GENERATOR_PATH.parse().unwrap() };
    let ca_path = if args.len() == 4 {
        &args[2]
    } else { &CA_PATH.parse().unwrap() };
    let wa_path = if args.len() == 4 {
        &args[3]
    } else { &WA_PATH.parse().unwrap() };

    let input_file_path = INPUT_FILE.parse().unwrap();
    let ca_output_file_path = CA_OUTPUT_FILE.parse().unwrap();
    let wa_output_file_path = WA_OUTPUT_FILE.parse().unwrap();

    println!("generator path: {generator_path}");
    println!("ca path: {ca_path}");
    println!("wa path: {wa_path}");
    println!("input file path: {input_file_path}");
    println!("ca output file path: {ca_output_file_path}");
    println!("wa output file path: {wa_output_file_path}");

    let mut test_count = 0;

    loop {
        match command::make_input_file(
            &generator_path,
            &input_file_path
        ) {
            Ok(file) => file,
            Err(e) => {
                println!("input file making error: {e}");
                return
            }
        };

        let ca_file = match command::make_output_file(
            &ca_path,
            &input_file_path,
            &ca_output_file_path
        ) {
            Ok(file) => file,
            Err(e) => {
                println!("ca output file making error: {e}");
                return
            }
        };

        let wa_file = match command::make_output_file(
            &wa_path,
            &input_file_path,
            &wa_output_file_path
        ) {
            Ok(file) => file,
            Err(e) => {
                println!("wa output file making error: {e}");
                return
            }
        };

        match test::test(ca_file, wa_file) {
            Ok(line_number) => {
                if line_number != 0 {
                    println!("differ at line {line_number}");
                    break;
                }
                else {
                    test_count += 1;
                    if test_count % 100 == 0 {
                        println!("{test_count} test passed");
                    }
                }
            },
            Err(e) => {
                println!("testing error: {e}");
                return
            }
        }
    }
}