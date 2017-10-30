import socketClient from 'socket.io-client'
// import { actions } from '../app.module'

const io = socketClient('http://localhost:8088/')

// io.on('message', (msg) => {
//   saveMessage(msg)
// })

export default io
