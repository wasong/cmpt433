import React from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'

import FlatCard from 'components/FlatCard'

const styles = {
  teamCard: {
    height: 400,
    margin: '0 40px 0 0',
    flex: 2,
  },
}

const Team = props => (
  <FlatCard rootStyles={styles.teamCard}>Team</FlatCard>
)

Team.propTypes = {}
Team.defaultProps = {}

export default Radium(Team)
