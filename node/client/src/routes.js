import React from 'react'
import Radium from 'radium'

import Dashboard from './Dashboard'

const styles = {
  display: 'flex',
  minHeight: '100vh',
}

export default Radium(() => (
  <div style={styles}>
    <Dashboard />
  </div>
))
