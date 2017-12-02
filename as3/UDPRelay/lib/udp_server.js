"use strict";
/*
 * Respond to commands over a websocket to relay UDP commands to a local program
 */

var socketio = require('socket.io');
var io;

var dgram = require('dgram');

exports.listen = function(server) {
	io = socketio.listen(server);
	
	io.sockets.on('connection', function(socket) {
		handleCommand(socket);
	});
};

function handleUDPConnection(socket, command, replyCommand) {
	socket.on(command, function(data) {
		console.log('command: ' + data);
		
		// Info for connecting to the local process via UDP
		var PORT = 12345;
		var HOST = '192.168.7.2';
		var buffer = new Buffer(data);

		var client = dgram.createSocket('udp4');
		client.send(buffer, 0, buffer.length, PORT, HOST, function(err, bytes) {
		    if (err) 
		    	throw err;
		    console.log('UDP message sent to ' + HOST +':'+ PORT + buffer);
		});
		
		client.on('listening', function () {
		    var address = client.address();
		    console.log('UDP Client: listening on ' + address.address + ":" + address.port);
		});
		// Handle an incoming message over the UDP from the local application.
		client.on('message', function (message, remote) {
		    console.log("UDP Client: message Rx" + remote.address + ':' + remote.port +' - ' + message);
		    
		    var reply = message.toString('utf8')
		    socket.emit(replyCommand, reply);
		    
		    client.close();

		});
		console.log('end call')
		client.on("UDP Client: close", function() {
		    console.log("closed");
		});
		client.on("UDP Client: error", function(err) {
		    console.log("error: ",err);
		});
	});
}

function handleCommand(socket) {
	// Passed string of command to relay
	handleUDPConnection(socket, "prime", "commandReply");
	handleUDPConnection(socket, "volume_monitor", "volume_monitor_reply");
	handleUDPConnection(socket, "tempo_monitor", "tempo_monitor_reply");
	handleUDPConnection(socket, "beat_monitor", "beat_monitor_reply");
};
