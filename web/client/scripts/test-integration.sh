#!/bin/bash

healthy=false

for i in {0..5}; do
  if curl --fail --silent http://mejai-api:8080; then
    healthy=true
    break
  fi
  echo "...pausing until app is up"
  sleep 5
done

if [ "$healthy" = false ]; then
  echo "Failed healthcheck"
  curl http://mejai-api:8080 --silent; echo
  exit 1
fi

# npm run test:integration
