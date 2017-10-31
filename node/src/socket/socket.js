import socketIO from 'socket.io'

import handleCommand from './UDPServer'

const listener = (server) => {
  const io = socketIO(server)
  io.on('connection', (socket) => {
    console.log('user connected')

    handleCommand(server)

    socket.on('message', (msg) => {
      console.log(`message: ${msg}`)
      io.emit('message', 'hi')
    })

    socket.on('disconnect', function(){
      console.log('user disconnected');
    });
  })
}

export default listener
