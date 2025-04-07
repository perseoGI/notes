set -e

for v in 5.29.3 5.28.3 5.27.0 4.25.3; do
    conan export recipes/protobuf/all --version $v
done

mkdir -p /tmp/protobuf/ && cd /tmp/protobuf/

conan lock add --requires=abseil/20230802.1
for abseil in 20230802.1 20240116.1 20240116.2; do
    conan lock update --requires=abseil/$abseil
    for v in 5.29.3 5.28.3 5.27.0 4.25.3; do
        conan install --requires=protobuf/$v --lockfile-partial --build=missing
    done
done


