"use strict";
// Client-side interactions with the browser.

// Web sockets: automatically establish a socket with the server
var socket = io.connect();

// Make connection to server when web page is fully loaded.
$(document).ready(function() {
	// Make the text-entry box have keyboard focus.
	$('#send-command').focus();
	
	// Allow sending the form (pressing enter).
	$('#send-form').submit(function() {
		readUserInput();
		
		// Return false to show we have handleded it.
		return false;
	});

	// Handle data coming back from the server
	socket.on('daAnswer', function(result) {
		$('#messages').append(divMessage(result));
	});
	
	socket.on('daError', function(result) {
		var msg = divMessage('SERVER ERROR: ' + result);
		$('#messages').append(msg);
	});
	
});

function readUserInput() {
	// Get the user's input from the browser.
	var message = $('#send-command').val();
	
	// Display the command in the message list.
	$('#messages').append(divMessage(message));

	// Process the command
	var systemMessage = processCommand(message);
	if (systemMessage != false) {
		$('#messages').append(divMessage(systemMessage));
	}
	
	// Scroll window.
	$('#messages').scrollTop($('#messages').prop('scrollHeight'));
	
	// Clear the user's command (ready for next command).
	$('#send-command').val('');
}

function processCommand(command) {
	var words = command.split(' ');
	var operation = words[1];
	var returnMessage = false;
	
	switch(operation) {
	case '+':
		// Convert arguments to numbers
		var x = Number(words[0]);
		var y = Number(words[2]);
		
		// Put numbers into a custom structure to send to server.
		var message = {
				addend1: x,
				addend2: y
		};
		socket.emit('daAdd', message);

		break;
	// ... more operations could go here..
	default:
		returnMessage = 'Unrecognized command.'
	}
	return returnMessage;
}

//Wrap a string in a new <div> tag
function divMessage(inString) {
	return $('<div></div>').text(inString);
}

