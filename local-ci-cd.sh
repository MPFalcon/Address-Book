#!/bin/bash

usage() {
    cat << EOF
    
Usage: $0 [-h] [-e] [-s]

    -s  Setup prerequisites for local CI/CD
    -e  Execute pipelines for local CI/CD
    -h  Show this message

@ Meredith Purifoy, Falcon Solutions, LLC 2024

EOF
}

setup () {
    echo "Setting up prerequesites for local CI/CD"
    curl --proto '=https' --tlsv1.2 -sSf https://raw.githubusercontent.com/nektos/act/master/install.sh | sudo bash
}

execute() {
    echo "Executing pipelines"
    act --workflows ".github/workflows/cmake-single-platform.yml" --secret-file "" --var-file "" --input-file "" --eventpath "" -P ubuntu-latest=catthehacker/ubuntu:act-latest
}

while getopts "ehs" opt; do
    case $opt in
        s)
            setup
            ;;
        e)
            execute
            ;;
        h)
            usage
            ;;
    esac
done

shift $((OPTIND - 1))

if [ $OPTIND -eq 1 ]; then
    echo "Arguments are required to run build script"
    usage
    exit 1
fi

# EOF
