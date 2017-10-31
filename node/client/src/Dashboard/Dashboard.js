import React, { Component } from 'react'
import Radium from 'radium'
import { Route } from 'react-router-dom'

import Home from './Home'

const styles = {
  root: {
    flex: 12,
    backgroundColor: '#f6f6f6',
  },
  navbarRoot: {
    padding: '0 25px',
    backgroundColor: '#fff',
  },
  gridIcon: {
    margin: '0 10px 0 0',
  },
}

class Dashboard extends Component {
  state = {}

  render() {
    return (
      <div style={styles.root}>
        <Route path="/" component={Home} />
      </div>
    )
  }
}

Dashboard.propTypes = {}
Dashboard.defaultProps = {}

export default Radium(Dashboard)
