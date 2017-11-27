import React from 'react'
import { Route } from 'react-router-dom'

export default () => (
  <div>
    <Route exact path="/" component={() => <div>Home</div>} />
    <Route path="/gallery" component={() => <div>Gallery</div>} />
  </div>
)
