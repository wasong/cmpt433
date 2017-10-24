import React, { Component } from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'
import { Route, Redirect, Switch } from 'react-router-dom'
import { Grid } from 'react-feather'

import Navbar from 'components/Navbar'

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
        <Navbar
          title="Project Kubernetes"
          icon={<Grid color="#e8e8ea" size={30} style={styles.gridIcon} />}
          rootStyles={styles.navbarRoot}
        />
        <Route path="/" component={Home} />
      </div>
    )
  }
}

Dashboard.propTypes = {}
Dashboard.defaultProps = {}

export default Radium(Dashboard)
