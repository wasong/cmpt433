import io from 'socket.io-client'

const socket = io('http://localhost:3000/')
socket.on('hello', (data) => {
  console.log(data)
})
