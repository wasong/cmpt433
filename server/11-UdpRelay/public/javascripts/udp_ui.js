"use strict";
// Client-side interactions with the browser.

// Make connection to server when web page is fully loaded.
var socket = io.connect();
$(document).ready(function() {

	$('#btnCount').click(function(){
		sendPrimeCommand("count");
	});
	$('#btnFirst').click(function(){
		sendPrimeCommand("first 5");
	});
	$('#btnLast').click(function(){
		sendPrimeCommand("last 5");
	});
	$('#btnStop').click(function(){
		sendPrimeCommand("stop");
	});
	
	socket.on('commandReply', function(result) {
		var newDiv = $('<div></div>').text(result);
		$('#messages').append(newDiv);
		$('#messages').scrollTop($('#messages').prop('scrollHeight'));
	});
	
});

function sendPrimeCommand(message) {
	socket.emit('prime', message);
};