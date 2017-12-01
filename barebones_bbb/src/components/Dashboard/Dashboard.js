import React, { Component } from 'react'
import Radium from 'radium'

import Monitors from './Monitors'
import Featured from './Featured'

const styles = {
  root: {
    display: 'flex',
  },
}

class Dashboard extends Component {
  state = {}

  render() {
    return (
      <div style={styles.root}>
        <Monitors />
        <Featured />
      </div>
    )
  }
}

export default Radium(Dashboard)
