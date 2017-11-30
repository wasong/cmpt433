import React from 'react'
import { Route } from 'react-router-dom'

import NavBar from 'components/NavBar'
import Gallery from 'components/Gallery'
import Home from 'components/Home'

const styles = {
  root: {
    minHeight: '100vh',
    display: 'flex',
    flexDirection: 'column',
    flex: 1,
  },
  content: {
    flex: 1,
    padding: 50,
    display: 'flex',
    flexDirection: 'column',
  },
}

export default () => (
  <div style={styles.root}>
    <NavBar />
    <div style={styles.content}>
      <Route exact path="/" component={Home} />
      <Route path="/gallery" component={Gallery} />
    </div>
  </div>
)
