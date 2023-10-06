#!/bin/bash

# 원본 파일 경로
original_file="./hello/CMakeLists.original.txt"

# 사용자로부터 디렉토리 이름 입력 받기
read -p "default 디렉토리를 복사할 새 디렉토리(application) 이름을 입력하세요: " new_dir_name

# hello 디렉토리를 새 디렉토리로 복사
cp -r hello "$new_dir_name"

echo "디렉토리 복사가 완료되었습니다."

# 새 파일 경로
new_file="$new_dir_name/CMakeLists.txt"

# 사용자로부터 A 단어 입력 받기
read -p "application 이름을 입력하세요(예: test): " a_word

# 사용자로부터 B 단어 입력 받기
read -p "application source file name를 입력하세요(예: test.c): " b_word

# 원본 파일이 존재하는지 확인
if [ ! -f "$original_file" ]; then
  echo "CMakeLists.original.txt 파일이 현재 default 디렉토리에 존재하지 않습니다."
  exit 1
fi

# 원본 파일을 새 파일로 복사
cp "$original_file" "$new_file"

# A 단어를 hello로, B 단어를 hello.c로 대체
sed -i "s/hello/$a_word/g; s/hello.c/$b_word/g" "$new_file"

echo "대체 작업이 완료되었습니다."

echo "소스 파일을 $new_dir_name 안에 작성/복사 한 뒤, $new_dir_name 에서 build 스크립트를 실행 해 주세요! "
