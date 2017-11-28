import React from 'react'
import { Route } from 'react-router-dom'

import PageHeader from 'components/PageHeader'
import Gallery from 'components/Gallery'
import Home from 'components/Home'

const styles = {
  root: {
    padding: 50,
  },
  content: {
    display: 'flex',
    flexDirection: 'column',
    // alignItems: 'center',
  },
}

export default () => (
  <div style={styles.root}>
    <PageHeader title="NodeJS" />
    <div style={styles.content}>
      <Route exact path="/" component={Home} />
      <Route path="/gallery" component={Gallery} />
    </div>
  </div>
)
