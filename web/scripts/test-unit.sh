#!/bin/bash

set -eo pipefail

echo "--- Linting"
yarn run test:lint

echo "--- Unit testing"
yarn run test:unit

echo "--- Dependencies security testing"
yarn run test:dependencies
