#!/usr/bin/env bash
# shellcheck disable=SC2155

export NAME="hello"
export DESCRIPTION="A C++ template"
export VERSION="4.0"
export HOMEPAGE_URL="https://github.com/otreblan/$NAME"
export YEAR=$(date +%Y)
export USER_NAME="Otreblan"
export USER_EMAIL="otreblain@gmail.com"

J2=j2

# Exit if jinja2 isn't installed.
which -- "${J2%%[ \t\n]*}" > /dev/null || exit 1

while IFS= read -rd "" filename; do
	$J2 "$filename" -o "${filename%.in}"
	mv --force "${filename%.in}" "$filename"
	git mv --verbose --force "$filename" "${filename%.in}"
done < <(find . -name "*.in" -print0)

git add -u
