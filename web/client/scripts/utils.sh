function package_version() {
  echo $(grep -m1 version package.json | awk -F: '{ print $2 }' | sed 's/[", ]//g')
}

function inline_image() {
  printf '\033]1338;url='"$1"';alt='"$2"'\a\n'
}
