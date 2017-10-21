'use strict';

Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.socketListener = exports.handleCommand = undefined;

var _socket = require('socket.io');

var _socket2 = _interopRequireDefault(_socket);

var _dgram = require('dgram');

var _dgram2 = _interopRequireDefault(_dgram);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

var handleCommand = exports.handleCommand = function handleCommand(socket) {
  // Passed string of command to relay
  socket.on('prime', function (data) {
    console.log('prime command: ' + data);

    // Info for connecting to the local process via UDP
    var PORT = 12345;
    var HOST = '127.0.0.1';
    var buffer = new Buffer(data);

    var client = _dgram2.default.createSocket('udp4');
    client.send(buffer, 0, buffer.length, PORT, HOST, function (err, bytes) {
      if (err) throw err;
      console.log('UDP message sent to ' + HOST + ':' + PORT);
    });

    client.on('listening', function () {
      var address = client.address();
      console.log('UDP Client: listening on ' + address.address + ' : ' + address.port);
    });
    // Handle an incoming message over the UDP from the local application.
    client.on('message', function (message, remote) {
      console.log('UDP Client: message Rx ' + remote.address + ' : ' + remote.port + ' - ' + message);

      var reply = message.toString('utf8');
      socket.emit('commandReply', reply);

      client.close();
    });

    client.on('UDP Client: close', function () {
      console.log('Closed');
    });
    client.on('UDP Client: error', function (err) {
      console.log('Error: ' + err);
    });
  });
};

var socketListener = exports.socketListener = function socketListener(server) {
  var io = _socket2.default.listen(server);
  io.set('log level 1');

  io.sockets.on('connection', function (socket) {
    socket.emit('hello', { hello: 'world' });
    handleCommand(socket);
  });
};

exports.default = {
  socketListener: socketListener,
  handleCommand: handleCommand
};