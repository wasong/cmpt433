import openSocket from 'socket.io-client'

const socket = openSocket(process.env.SOCKET_PORT)

// const sendCommand = (command = 'prime', message = 'help') => {
//   // command is the emit socket identifier, message is used to select the function
//   socket.emit(command, message)
// }

// const onReply = (reply = 'default', cb) => {
//   socket.on(reply, cb)
// }

export default socket
