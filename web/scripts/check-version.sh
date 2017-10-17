#!/bin/bash

source ./scripts/utils.sh

VERSION=v$(package_version)

curl \
  -H "Authorization: token ${GITHUB_RELEASE_ACCESS_TOKEN}" \
  --fail --silent \
  # insert github tag url here
  > /dev/null

if [ $? -eq 0 ]; then
  inline_image "http://i.giphy.com/l2Sqb2raeiZLVDFaU.gif" "failed"
  echo "Release of version ${VERSION} already exists. Update package version."
  exit 1
fi
