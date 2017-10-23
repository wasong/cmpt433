import React, { Component } from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'

const styles = {
  root: {
    flex: 4,
  },
}

class Sidebar extends Component {
  state = {}

  render() {
    return (
      <div style={styles.root}>
        Sidebar
      </div>
    )
  }
}

Sidebar.propTypes = {}
Sidebar.defaultProps = {}

export default Radium(Sidebar)
