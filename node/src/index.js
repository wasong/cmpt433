import "babel-polyfill"
import express from 'express'
import http from 'http'
import path from 'path'

import io from './socket'

const PORT = 8088
const app = express()
const httpServer = http.createServer(app)
app.use(express.static(path.resolve(__dirname, '..', 'client', 'public')))

app.use('/', (req, res) => {
  res.sendFile('/index.html')
})

httpServer.listen(PORT, (req, res) => {
  console.log(`Listening on PORT ${PORT}`)
})

// start socket server
io(httpServer)
