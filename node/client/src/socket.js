import io from 'socket.io-client'

const socket = io('http://localhost')
socket.on('hello', (data) => {
  console.log(data)
})
