'use strict';

var _express = require('express');

var _express2 = _interopRequireDefault(_express);

var _bodyParser = require('body-parser');

var _bodyParser2 = _interopRequireDefault(_bodyParser);

var _morgan = require('morgan');

var _morgan2 = _interopRequireDefault(_morgan);

var _path = require('path');

var _path2 = _interopRequireDefault(_path);

var _http = require('http');

var _http2 = _interopRequireDefault(_http);

var _socket = require('./lib/socket');

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

var app = (0, _express2.default)();
var PORT = process.env.PORT || 4000;

app.use(_bodyParser2.default.json());
app.use(_bodyParser2.default.urlencoded({ extended: true }));
app.use((0, _morgan2.default)('combined'));

// expose static files
// dirname = '/public/dist'
app.use(_express2.default.static(_path2.default.resolve(__dirname, '..')));
app.use(_express2.default.static(_path2.default.resolve(__dirname, '..', 'index.html')));

app.get('*', function (req, res) {
  res.sendFile(_path2.default.resolve(__dirname, '..', 'index.html'));
});

// separate http server but also maintain express routes and middleware
app.server = _http2.default.createServer(app);

// start socket listener
(0, _socket.socketListener)(app.server);

app.server.listen(PORT, function () {
  console.log('Listening on PORT: ' + PORT);
});