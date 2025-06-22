#! /bin/bash

function colors_enabled
{
  # Cf. https://unix.stackexchange.com/questions/9957/how-to-check-if-bash-can-print-colors
  if [ -t 1 ] ; then
    local colors="$(tput colors)"
    [ "$colors" ] && [ "$colors" -ge 8 ]
  else
    false
  fi
}

function print_ellip_right
{
  local text="$1" fill_to="$2"
  local text_len="${#text}"
  local count=$((fill_to - text_len - 2))
  [[ "$count" -ge 3 ]] || count=3
  echo -n "${text} "
  while [ "$count" -gt 0 ] ; do
    echo -n '.'
    count=$((count - 1))
  done
  echo -n " "
}

if colors_enabled ; then
  red="\033[31m"
  green="\033[32m"
  reset="\033[00m"
else
  red=""
  green=""
  reset=""
fi  

status=0

for name in $(ls | sort) ; do
  if [[ "$name" =~ _test_suite$ ]] ; then
    print_ellip_right "$name" 60
    output=$("./${name}" 2>&1)
    if [ $? -eq 0 ] ; then
      echo -e "${green}ok${reset}"
    else
      echo -e "${red}failed${reset}"
      echo -e "${red}${output}${reset}" >&2
      status=1
    fi
  fi
done

exit "$status"
