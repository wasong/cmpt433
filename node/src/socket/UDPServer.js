import dgram from 'dgram'

const handleCommand = (socket) => {
  // Passed string of command to relay
  socket.on('help', (data) => {
    console.log(`help command: ${data}`)

    // Info for connecting to the local process via UDP
    const PORT = 12345
    const HOST = '192.168.7.2'
    const buffer = new Buffer(data)

    const client = dgram.createSocket('udp4')
    client.send(buffer, 0, buffer.length, PORT, HOST, (err, bytes) => {
      if (err) throw err
      console.log(`UDP message sent to ${HOST}:${PORT}`)
    })

    client.on('listening', () => {
      const address = client.address()
      console.log(`UDP Client: listening on ${address.address} : ${address.port}`)
    })
    // Handle an incoming message over the UDP from the local application.
    client.on('message', (message, remote) => {
      console.log(`UDP Client: message Rx ${remote.address} : ${remote.port} - ${message}`)

      const reply = message.toString('utf8')
      socket.emit('commandReply', reply)

      client.close()
    })

    client.on('UDP Client: close', () => {
      console.log('Closed')
    })
    client.on('UDP Client: error', (err) => {
      console.log(`Error: ${err}`)
    })
  })
}

export default handleCommand
