const express = require('express')
const serve = require('serve-static')
const https = require('https')
const path = require('path')
const fs = require('fs')

const app = express()

const PORT = 8088

// html/images dirs
const html = path.join(__dirname, 'public', 'index.html')
const publicDir = path.join(__dirname, 'public')
const images = path.join(__dirname, '..', '..', 'public', 'myApps', 'pictures')

// https keys
const options = {
  key: fs.readFileSync('./key.pem'),
  cert: fs.readFileSync('./key-cert.pem'),
}

app.use(express.static(publicDir))
app.use(express.static(html))
app.use(serve(images))

app.get('*', (req, res) => {
  res.sendFile(html)
})

const server = https.createServer(options, app).listen(PORT, () => {
  console.log(`Listening on ${PORT}`)
})

// const udpServer = require('./lib/udp_server');
// const procServer = require('./lib/proc_uptime');
// udpServer.listen(server);
