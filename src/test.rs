use std::fs::File;
use std::io::{self, BufRead, BufReader};

/// 두 파일을 비교해 최초로 다른 줄 번호 반환
/// 반환값:
/// - Ok(line_number): 최초로 다른 줄 번호 (1부터 시작)
/// - Ok(0): 두 파일의 모든 줄이 동일
/// - Err(e): 파일 읽기 중 오류 발생
pub(crate) fn test(
    ca_output: File,
    wa_output: File
) -> io::Result<i32> {
    let mut ca_reader
        = BufReader::new(ca_output).lines();
    let mut wa_reader
        = BufReader::new(wa_output).lines();

    let mut line_number = 0;

    loop {
        line_number += 1;

        let ca = ca_reader.next();
        let wa = wa_reader.next();

        match (ca, wa) {
            // 한쪽 파일에서 읽기 에러 발생 시, 에러를 호출자에게 전파
            (Some(Err(e)), _) | (_, Some(Err(e))) => {
                return Err(e);
            }

            // 두 줄 모두 성공적으로 읽은 경우, 내용 비교
            (Some(Ok(ca)), Some(Ok(wa))) => {
                if ca != wa {
                    return Ok(line_number); // 최초로 다른 줄 번호 반환
                }
            }

            // 두 파일 모두 끝에 도달
            (None, None) => break,

            // 한 파일만 끝에 도달한 경우
            _ => {
                return Ok(line_number); // 다른 줄 번호 반환
            }
        }
    }

    Ok(0) // 파일이 동일한 경우 0 반환
}