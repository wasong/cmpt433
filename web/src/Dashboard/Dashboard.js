import React, { Component } from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'
import { Route, Redirect, Switch } from 'react-router-dom'

import Navbar from 'components/Navbar'

const styles = {
  root: {
    flex: 10,
    backgroundColor: '#f6f6f6',
  },
  navbarRoot: {
    backgroundColor: '#fff',
  },
}

class Dashboard extends Component {
  state = {}

  render() {
    return (
      <div style={styles.root}>
        <Navbar
          title="Project Kubernetes"
          rootStyles={styles.navbarRoot}
        />
      </div>
    )
  }
}

Dashboard.propTypes = {}
Dashboard.defaultProps = {}

export default Radium(Dashboard)
