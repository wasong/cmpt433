import socketIO from 'socket.io'

const listener = (server) => {
  const io = socketIO(server)
  io.on('connection', (socket) => {
    console.log('user connected')
    socket.on('disconnect', function(){
      console.log('user disconnected');
    });
  })
}

export default listener
