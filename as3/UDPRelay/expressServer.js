var express = require('express')
var serve = require('serve-static')
var https = require('https')
var path = require('path')
var fs = require('fs')

var app = express()

const PORT = 8088

// html/images dirs
var html = path.join(__dirname, 'public', 'index.html')
var public = path.join(__dirname, 'public')
var images = path.join(__dirname, '..', '..', '..', 'public', 'myApps', 'pictures')

// https keys
var options = {
	key:  fs.readFileSync('./key.pem'),
	cert: fs.readFileSync('./key-cert.pem')
}

app.use(express.static(public))
app.use(express.static(html))
app.use(serve(images))

app.get('*', function (req, res) {
  res.sendFile(html)
})

var server = https.createServer(options, app).listen(PORT)

// var udpServer = require('./lib/udp_server');
// var procServer = require('./lib/proc_uptime');
// udpServer.listen(server);

