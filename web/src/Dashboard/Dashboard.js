import React, { Component } from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'
import { Route, Redirect, Switch } from 'react-router-dom'

const styles = {
  root: {
    flex: 10,
  },
}

class Dashboard extends Component {
  state = {}

  render() {
    return (
      <div style={styles.root}>
        Dashboard
      </div>
    )
  }
}

Dashboard.propTypes = {}
Dashboard.defaultProps = {}

export default Radium(Dashboard)
