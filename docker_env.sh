docker build -t s1_dev_env .
docker run --rm -it -v $(pwd):/s1 s1_dev_env "/bin/bash"