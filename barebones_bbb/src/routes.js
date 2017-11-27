import React from 'react'
import { Route } from 'react-router-dom'

import PageHeader from 'components/PageHeader'
import Gallery from 'components/Gallery'

const styles = {
  root: {
    display: 'flex',
    flexDirection: 'column',
    alignItems: 'center',
  },
}

export default () => (
  <div style={styles.root}>
    <PageHeader title="NodeJS" />
    <Route exact path="/" component={() => <div>Home</div>} />
    <Route path="/gallery" component={Gallery} />
  </div>
)
