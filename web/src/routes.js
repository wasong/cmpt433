import React from 'react'
import Radium from 'radium'

import Dashboard from './Dashboard'
import Sidebar from './Sidebar'

const styles = {
  display: 'flex',
  minHeight: '100vh',
}

export default Radium(() => (
  <div style={styles}>
    <Sidebar />
    <Dashboard />
  </div>
))
