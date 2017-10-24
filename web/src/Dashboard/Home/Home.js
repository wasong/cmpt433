import React, { Component } from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'

import FlatCard from 'components/FlatCard'

const styles = {
  root: {
    display: 'flex',
    padding: 40,
  },
  teamCard: {
    margin: '0 40px 0 0',
    flex: 2,
  },
  projectCard: {
    flex: 6,
  },
}

class Home extends Component {
  state = {}

  render() {
    return (
      <div style={styles.root}>
        <FlatCard rootStyles={styles.teamCard}>Team</FlatCard>
        <FlatCard rootStyles={styles.projectCard}>Project Activity</FlatCard>
      </div>
    )
  }
}

Home.propTypes = {}
Home.defaultProps = {}

export default Radium(Home)
