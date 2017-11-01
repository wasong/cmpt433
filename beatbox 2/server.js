// After creating package.json, install modules:
//   $ npm install
//
// Launch server with:
//   $ node server.js
var PORT_NUMBER = 8088;

// HTTPS:
var http = require('https');

// var http = require('http');
var fs   = require('fs');
var path = require('path');
var mime = require('mime');

// HTTPS:
var options = {
		key:  fs.readFileSync('./key.pem'),
		cert: fs.readFileSync('./key-cert.pem')
}

/* 
 * Create the static web server
 */
// HTTPS:
var server = http.createServer(options, function(request, response) {
	var filePath = false;
	
	if (request.url == '/') {
		filePath = 'public/index.html';
	} else {
		filePath = 'public' + request.url;
	}
	
	var absPath = './' + filePath;
	serveStatic(response, absPath);
});

server.listen(PORT_NUMBER, function() {
	console.log("Server listening on port " + PORT_NUMBER);
});

function serveStatic(response, absPath) {
	fs.exists(absPath, function(exists) {
		if (exists) {
			fs.readFile(absPath, function(err, data) {
				if (err) {
					send404(response);
				} else {
					sendFile(response, absPath, data);
				}
			});
		} else {
			send404(response);
		}
	});
}

function send404(response) {
	response.writeHead(404, {'Content-Type': 'text/plain'});
	response.write('Error 404: resource not found.');
	response.end();
}

function sendFile(response, filePath, fileContents) {
	response.writeHead(
			200,
			{"content-type": mime.lookup(path.basename(filePath))}
		);
	response.end(fileContents);
}

/*
 * Create the Beat-box server to listen for the websocket
 */
var beatServer = require('./lib/beat_server');
beatServer.listen(server);