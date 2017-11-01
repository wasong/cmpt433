// Disables creation of variables without declaration
"use strict";

/*
 * Respond to commands over a websocket to ...
 */
// HTTPS:
var fs = require('fs');
var socketio = require('socket.io');
var io;

var dgram = require('dgram');

exports.listen = function(server) {
	io = socketio.listen(server);
	io.set('log level 1');
	
	io.sockets.on('connection', function(socket) {
		handleCommand(socket);
	});
};

function handleCommand(socket) {

	// Passed string of command to relay
	socket.on('udp', function(data) {

		// Info for connecting to the local process via UDP
		var PORT = 12345;
		var HOST = '192.168.7.2';
		var buffer = new Buffer(data);

		var client = dgram.createSocket('udp4');
		client.send(buffer, 0, buffer.length, PORT, HOST, function(err, bytes) {
		    if (err) 
		    	throw err;
		    console.log('UDP message sent to ' + HOST +':'+ PORT);
		});

		client.on('listening', function () {
		    var address = client.address();
		    console.log('UDP Client: listening on ' + address.address + ":" + address.port);
		});

		client.on('message', function (message, remote) {
			console.log("UDP Client: message Rx" + remote.address + ':' + remote.port + ' - ' + message);

			var reply = message.toString('utf8');
			var type = reply.substring(0, reply.lastIndexOf(':'));
			var response = reply.substring(reply.lastIndexOf(':')).replace(':', '');
			console.log('Response: '+ response);
			
			if (type == 'vol-' || type == 'vol+')
			{
				socket.emit('newVolume', response);
			}
			else if (type == 'tempo-' || type == 'tempo+')
			{
				socket.emit('newTempo', response);
			}
			else if (type == 'beat')
			{
				socket.emit('newBeat', response);
			}
			else if (type == 'sound')
			{
				socket.emit('newSound', response);
			}

			client.close();
		});

		client.on("UDP Client: close", function() {
			console.log("closed");
		});
		client.on("UDP Client: error", function() {
			console.log("error: ", err);
		});
	});

	socket.on('proc', function(fileName) {
		var absPath = "/proc/" + fileName;
		console.log('accessing ' + absPath);

		fs.exists(absPath, function(exists) {
			if (exists) {
				// Can use 2nd param: 'utf8', 
				fs.readFile(absPath, function(err, fileData) {
					if (err) {
						emitSocketData(socket, fileName, 
								"ERROR: Unable to read file " + absPath);
					} else {
						emitSocketData(socket, fileName, 
								fileData.toString('utf8'));
					}
				});
			} else {
				emitSocketData(socket, fileName, 
						"ERROR: File " + absPath + " not found.");
			}
		});
	});
};

function emitSocketData(socket, fileName, contents) {
	var result = {
			fileName: fileName,
			contents: contents
	}
	socket.emit('fileContents', result);	
}