#!/bin/sh

command -v python  >/dev/null 2>&1 || { echo >&2 "I require 'python' but it's not installed. Please install it or activate a virtual environment. Aborting."; return; }

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"

for f in *.py; do
  echo "Testing ->  $f";
  python "$f" -v;
done
