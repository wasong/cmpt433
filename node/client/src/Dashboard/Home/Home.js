import React, { Component } from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'

import ProjectActivity from './ProjectActivity'

const styles = {
  root: {
    display: 'flex',
    padding: 40,
  },
}

class Home extends Component {
  state = {}

  render() {
    return (
      <div style={styles.root}>
        <ProjectActivity />
      </div>
    )
  }
}

Home.propTypes = {}
Home.defaultProps = {}

export default Radium(Home)
