use std::io::Result;
use std::fs::File;
use std::process::{Command, Stdio};

pub(crate) fn make_input_file(
    generator_path: &String,
    file_path: &String
) -> Result<File> {

    let input_file = File::create(file_path)?;
    let new_std_out = Stdio::from(input_file);

    Command::new(generator_path)
        .stdout(new_std_out)
        .status()?;

    File::open(file_path)
}

pub(crate) fn make_output_file(
    solver_path: &String,
    input_file_path: &String,
    output_file_path: &String
) -> Result<File> {

    let input_file = File::open(input_file_path)?;
    let new_std_in = Stdio::from(input_file);

    let output_file = File::create(output_file_path)?;
    let new_std_out = Stdio::from(output_file);

    Command::new(solver_path)
        .stdin(new_std_in)
        .stdout(new_std_out)
        .status()?;

    File::open(output_file_path)
}