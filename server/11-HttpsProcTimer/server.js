"use strict";
// Demo server for HTTPS, accessing /proc
// Install modules:
//   $ npm install
//
// Launch server with:
//   $ node server.js
// 
// HTTPS Changes
// ------------------------
//	1. Generate private key in base folder of project
//	   $ openssl genrsa 1024 > key.pem
//	2. Generate public certificate (unsigned)
//	   $ openssl req -x509 -new -key key.pem > key-cert.pem
//	3. Code:
//	  a) require('https')
//	  b) options struct for private/public key
//	  c) pass options to http.createServer
//	4. HTML: link to https:// jQuery:
//	  <script src='https://code.jquery.com/jquery-1.8.0.min.js' type='text/javascript'></script>
// 
// See "HTTPS CHANGE" comments here and in index.html for more.

var PORT_NUMBER = 3042;

//HTTPS CHANGE #1: 
var http = require('https');

var fs   = require('fs');
var path = require('path');
var mime = require('mime');


// HTTPS CHANGE #2: Create options for the authentication
var options = {
		key:  fs.readFileSync('./key.pem'),
		cert: fs.readFileSync('./key-cert.pem')
}


/* 
 * Create the static web server
 */
//HTTPS CHANGE #3: 
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
	console.log("Server listeneing on port " + PORT_NUMBER);
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
 * Create the Proc-access server to listen for the websocket
 */
var procServer = require('./lib/proc_server');
procServer.listen(server);
