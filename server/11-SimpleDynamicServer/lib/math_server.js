/*
 * Respond to commands over a websocket to do math
 */

var socketio = require('socket.io');
var io;

exports.listen = function(server) {
	io = socketio.listen(server);
	io.set('log level 1');
	
	io.sockets.on('connection', function(socket) {

		handleCommand(socket);
	});
	
	
};

function handleCommand(socket) {
	var errorTimer = setTimeout(function() {
		socket.emit("daError", "Oops: User too slow at sending first command.");
	}, 5000);
	
	socket.on('daAdd', function(data) {
		// data is a structure with:
		//	.addend1: First number to be added
		//  .addend2: Second number to be added
		var val1 = Number(data.addend1);
		var val2 = Number(data.addend2)
		console.log('Adding ' + val1 + ' + ' + val2);
		
		var answer = doDaAddition(val1, val2);
		var message = val1 + ' + ' + val2 + ' = ' + answer;
		
		// Build and send reply.
		socket.emit('daAnswer', message);
		
		// Stop the timer:
		clearTimeout(errorTimer);
	});
	
	// ... add more commands here...
	socket.on('daSub', function(data){
		// ...
	});
};

function doDaAddition(x, y) {
	return x + y;
}

