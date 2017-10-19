import Express from 'express'
import bodyParser from 'body-parser'
import http from 'http'
import morgan from 'morgan'
import path from 'path'

import { socketListener } './socket'

const app = Express()
const PORT = process.env.PORT || 4000

app.use(bodyParser.json())
app.use(bodyParser.urlencoded({ extended: true }))
app.use(morgan('combined'))

// expose static files
// dirname = '/public'
app.use(Express.static(path.resolve(__dirname, '..')))

app.get('*', (req, res) => {
  res.sendFile(path.resolve(__dirname, '..', 'index.html'))
})

// separate http server but also maintain express routes and middleware
app.server = http.createServer(app)

// start socket listener
socketListener(app.server)

app.server.listen(PORT, () => {
  console.log(`Listening on PORT: ${PORT}`)
})
