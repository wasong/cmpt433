/*
* Respond to commands over a websocket to relay UDP commands to a local program
*/

const socketio = require('socket.io')
const dgram = require('dgram')

const handleUDPConnection = (socket, command, replyCommand) => {
  socket.on(command, (data, args = null) => {
    console.log(`'Command: ${data} ${args}`)
    // Info for connecting to the local process via UDP
    const PORT = 12345
    const HOST = '192.168.7.2'
    let bufferData = null

    if (data === 'setCode') {
      bufferData = `${data} ${args.length ? args.length : ''} ${args}`
    } else if (data === 'setSound') {
      bufferData = `${data} ${args}`
    } else {
      bufferData = data
    }

    const buffer = new Buffer(bufferData)

    const client = dgram.createSocket('udp4')
    client.send(buffer, 0, buffer.length, PORT, HOST, (err, bytes) => {
      if (err) throw err
      console.log(`UDP message sent to ${HOST}:${PORT}${buffer}`)
    })

    client.on('listening', () => {
      const address = client.address()
      console.log(`UDP Client: listening on ${address.address}:${address.port}`)
    })

    // Handle an incoming message over the UDP from the local application.
    client.on('message', (message, remote) => {
      console.log(`UDP Client: message Rx ${remote.address}:{remote.port}-${message}`)

      const reply = message.toString('utf8')
      socket.emit(replyCommand, reply)

      client.close()
    })

    console.log('end call')
    client.on('UDP Client: close', () => {
      console.log('closed')
    })

    client.on('UDP Client: error', (err) => {
      console.log('error: ', err)
    })
  })
}

const listen = (server) => {
  const io = socketio.listen(server)

  io.sockets.on('connection', (socket) => {
    // Passed string of command to relay
    handleUDPConnection(socket, 'prime', 'default')
    handleUDPConnection(socket, 'setCode', 'setCodeResponse')
    handleUDPConnection(socket, 'getCode', 'getCodeResponse')
    handleUDPConnection(socket, 'getAlarm', 'getAlarmResponse')
    handleUDPConnection(socket, 'setSound', 'setSoundResponse')
    handleUDPConnection(socket, 'getSound', 'getSoundResponse')
  })
}

module.exports = {
  listen,
}
