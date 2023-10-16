# build 디렉토리 생성
mkdir -p build

# build 디렉토리로 이동
cd build

# cmake .. 실행
cmake .. -G Ninja

# make 실행
ninja

echo "빌드가 완료되었습니다."
